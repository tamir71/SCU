Smalltalk at: #t put: nil!
t := Tree new!

t insert: 15!
t insert: 10!
t insert: 20!
t insert: 5!
t insert: 30!
t insert: 25!

(t member: 15) printNl!
(t member: 5) printNl!
(t member: 25) printNl!
(t member: 7) printNl!
(t member: 11) printNl!
(t member: 44) printNl!
