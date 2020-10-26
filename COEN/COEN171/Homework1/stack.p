program StackExample(input, output);
    type
	nodeptr = ^node;
	node = record
	    data : integer;
	    next : ^node
	end;

    procedure push(var head : nodeptr; x : integer);
        var cell : nodeptr;
    begin
	new(cell);
	cell^.data := x;
	cell^.next := head;
	head := cell
    end;

    function pop(var head : nodeptr) : integer;
	var cell : nodeptr;
    begin
	pop := head^.data;
	cell := head;
	head := head^.next;
	dispose(cell)
    end;

    function empty(head : nodeptr) : boolean;
    begin
	empty := head = nil
    end;

    var head : nodeptr;
	i : integer;

begin
    head := nil;

    for i := 1 to 10 do
	push(head, i);

    while not empty(head) do
	writeln(pop(head))
end.
