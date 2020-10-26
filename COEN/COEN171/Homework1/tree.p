{ Tamir Enkhjargal
  SCU - COEN 171
  Homework 1 - tree.p }


program bstree(input, output);

type tree = ^node;
	node = record
        info : integer;
        left : ^node;
        right: ^node;
    end;

function insert(var root : tree; value : integer) : tree; begin
    if root = nil then begin
            new(root);
            root^.left := nil;
            root^.right := nil;
            root^.info := value;
    end
    else if root^.info < value then
        root^.right := insert(root^.right, value)
    else if root^.info > value then
        root^.left := insert(root^.left, value);
    insert := root
end;

function member(root : tree; value : integer) : integer; begin
    if root = nil then
        member := 0
    else if root^.info = value then
        member := 1
    else if root^.info < value then
        member := member(root^.right, value)
    else
        member := member(root^.left, value)
end;

var t : tree;
var x : integer;
begin
    t := nil;
    readln(x);
    if x <> -1 then begin
    	repeat
        	t := insert(t, x);
        	readln(x);
    	until x = -1;
    end;
    readln(x);
    if x <> -1 then begin
    	repeat
        	if member(t, x) = 1 then
            	writeln('true')
        	else
            	writeln('false');
            	readln(x);
    	until x = -1;
    end;
end.
