Object subclass: #List
    instanceVariableNames: 'first'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'examples'!


!List methodsFor: 'adding'!

addFirst: anObject
    first := (Node data: anObject) linkTo: first
!

addLast: anObject
    | current |
    first isNil
	ifTrue: [first := Node data: anObject]
	ifFalse: [
	    current := first .
	    [ current link isNil ] whileFalse: [ current := current link ] .
	    current linkTo: (Node data: anObject) ]
!!


!List methodsFor: 'removing'!

removeFirst
    | data |
    first = nil ifFalse: [data := first data . first := first link].
    ^data
!

removeLast
    | current fred |
    first isNil ifTrue: [^nil] .

    current := first .
    [ current link isNil ]
	whileFalse: [ fred := current . current := current link ] .
    fred isNil ifTrue: [ first := nil ] ifFalse: [ fred linkTo: nil ] .
    ^current data
!!


!List methodsFor: 'enumerating'!

do: aBlock
    | current |
    current := first .
    [ current isNil ]
	whileFalse: [aBlock value: current data . current := current link]
!!


Smalltalk at: #x put: nil!

x := List new!
1 to: 4 do: [ :y | x addLast: y]!
x do: [:value | value printNl]!
x removeLast printNl!
x removeLast printNl!
x removeLast printNl!
x removeLast printNl!
x removeLast printNl!
