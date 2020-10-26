Object subclass: #Node
    instanceVariableNames: 'value left right'
    classVariableNames: ''
    poolDictionaries: ''


!Node methodsFor: 'initialization'!

value: anObject
    value := anObject
!!


!Node methodsFor: 'manipulation'!

member: anObject
    anObject < value
	ifTrue: [left = nil
		 ifTrue: [^false]
		 ifFalse: [^left member: anObject]].

    anObject > value
	ifTrue: [right = nil
		 ifTrue: [^false]
		 ifFalse: [^right member: anObject]].

    ^true.
!

insert: anObject
    anObject < value
	ifTrue: [left = nil
		 ifTrue: [left := Node new value: anObject]
		 ifFalse: [left insert: anObject]].

    anObject > value
	ifTrue: [right = nil
		 ifTrue: [right := Node new value: anObject]
		 ifFalse: [right insert: anObject]].
!!


Object subclass: #Tree
    instanceVariableNames: 'root'
    classVariableNames: ''
    poolDictionaries: ''

!Tree methodsFor: 'manipulation'!

member: anObject
    root isNil
	ifTrue: [^false]
	ifFalse: [^root member: anObject].
!

insert: anObject
    root isNil
	ifTrue: [root := Node new value: anObject]
	ifFalse: [root insert: anObject].
!!
