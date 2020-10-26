Object subclass: #Complex
    instanceVariableNames: 'real imag'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'examples'!


!Complex class methodsFor: 'instance creation'!

new
    ^super new real: 0 imaginary: 0
!

real: rNum imaginary: iNum
    ^super new real: rNum imaginary: iNum
!!


!Complex methodsFor: 'component access'!

real
    "Answer the real component of this number."
    ^real
!

imaginary
    "Answer the imaginary component of this number."
    ^imag
!

real: rNum imaginary: iNum
    "Set the real and imaginary components of this number."
    real := rNum .
    imag := iNum
!!


!Complex methodsFor: 'arithmetic'!

+ aComplex
    "Add two numbers and answer the result."
    ^Complex real: real + aComplex real
	imaginary: imag + aComplex imaginary
!

- aComplex
    "Subtract two numbers and answer the result."
    ^Complex real: real - aComplex real
	imaginary: imag - aComplex imaginary
!!


!Complex methodsFor: 'printing'!
printOn: aStream
    aStream print: real .
    imag < 0
	ifTrue: [aStream nextPutAll: ' - '; print: imag abs]
	ifFalse: [aStream nextPutAll: ' + '; print: imag] .
    aStream nextPut: $i
!!


Smalltalk at: #x put: nil!
Smalltalk at: #y put: nil!

x := Complex real: 4 imaginary: 1!
y := Complex real: 4 imaginary: 8 negated!

x printNl!
y printNl!
(x + y) printNl!
(x - y) printNl!
