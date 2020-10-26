Object subclass: #Stack
    instanceVariableNames: 'contents'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'examples'!


!Stack class methodsFor: 'instance creation'!
new
    ^super new initialize
!!


!Stack methodsFor: 'initialization'!
initialize
    contents := OrderedCollection new
!!


!Stack methodsFor: 'accessing'!
push: anElement
    contents addLast: anElement
!

pop
    ^contents removeLast
!!


Smalltalk at: #x put: nil!
x := Stack new!

x push: 1!
x push: 'hello'!
x push: x!

x pop printNl!
x pop printNl!
(x pop + 5) printNl!
