Object subclass: #Node
    instanceVariableNames: 'data link'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'examples'!


!Node class methodsFor: 'instance creation'!
data: anObject
    ^self new initialize: anObject
!!


!Node methodsFor: 'access'!
data
    ^data
!

link
    ^link
!

initialize: anObject
    data := anObject
!

linkTo: aNode
    link := aNode
!!
