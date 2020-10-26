program sort(input, output);
    const high = 8;
    type numbers = array[1 .. high] of integer;
    var a : numbers;

    procedure readarray;
	var i : integer;
    begin
	for i := 1 to high do
	    readln(a[i])
    end;

    procedure writearray;
	var i : integer;
    begin
	for i := 1 to high do
	    write(a[i], ' ');
	writeln
    end;

    procedure quicksort(var a : numbers; m, n : integer);
	var i : integer;

	function partition(var a : numbers; y, z : integer) : integer;
	    var i, j, x : integer;

	    procedure exchange(var a, b : integer);
		var t : integer;
	    begin
		t := a;
		a := b;
		b := t
	    end;

	begin
	    x := a[y];
	    i := y - 1;
	    j := z + 1;

	    while i < j do begin
		repeat
		    j := j - 1
		until a[j] <= x;

		repeat
		    i := i + 1
		until a[i] >= x;

		if i < j then
		    exchange(a[i], a[j]);
	    end;

	    partition := j
	end;

    begin
	if n > m then begin
	    i := partition(a, m, n);
	    writeln(i);
	    writearray;
	    quicksort(a, m, i);
	    quicksort(a, i + 1, n)
	end
    end;

begin
    readarray;
    quicksort(a, 1, high);
    writearray
end.
