Object subclass: PayrollSystem [
    PayrollSystem class >> new [
        ^super new.
    ]

    PayrollSystem >> readFrom: fileName [
    | file employees |

    Display display: 'Reached here1' displayNL.

    file := FileStream readOnlyFileNamed: fileName.
    employees := OrderedCollection new. 

    [file atEnd] whileFalse: [
        | lineParts employee |

        lineParts := (file nextLine) split: ' '.
        Display display: 'Line parts: ' , lineParts asString displayNL.

        "Parse lineParts to determine employee type and create appropriate employee instance"
        employee := self createEmployeeFromLine: lineParts.
        Display display: 'Employee: ' , employee printString displayNL.

        "Add the employee to the collection"
        employees add: employee.
    ].

    file close.
    ^employees asArray. "Convert the ordered collection to an array"
]


    PayrollSystem >> createEmployeeFromLine: lineParts [
    | type employee |

    type := lineParts first.

    "Check the type of employee and create the appropriate instance"
    employee := type = 'salaried' ifTrue: [
        SalariedEmployee newWith: lineParts second and: lineParts third and: lineParts fourth asNumber
    ] ifFalse: [type = 'hourly' ifTrue: [
        HourlyEmployee newWith: lineParts second and: lineParts third  and: lineParts fourth asNumber and: lineParts fifth asNumber
    ] ifFalse: [type = 'commission' ifTrue: [
        CommissionEmployee newWith: lineParts second and: lineParts third and: lineParts fourth asNumber and: lineParts fifth asNumber and: lineParts sixth asNumber
    ] ifFalse: [
        self error: 'Unknown employee type: ', type.
    ]]].

    ^employee
]






    PayrollSystem >> calculatePayroll: employees [
        "Iterate through each employee and print their payroll information"
        employees do: [:employee |
            | name payroll |

            name := employee getInfo.
            payroll := employee getEarning.

            Display display: name, ' - Payroll: $', payroll asString; displayNL.
        ].
    ]

    PayrollSystem >> check: value op: op threshold: threshold [
        op = 'eq' ifTrue: [ ^ value = threshold ].
        op = 'ne' ifTrue: [ ^ value ~= threshold ].
        op = 'ge' ifTrue: [ ^ value >= threshold ].
        op = 'le' ifTrue: [ ^ value <= threshold ].
        op = 'gt' ifTrue: [ ^ value > threshold ].
        op = 'lt' ifTrue: [ ^ value < threshold ].
        ^ false.
    ]

    PayrollSystem >> main: args [
    | employees fileName countThreshold operation conditionValue conditionOp result flagIndex|

    Display display: 'Reached here3' displayNL.

    "Parse command line arguments"
    flagIndex := args indexOf: '-f'.
    flagIndex ifNil: [self error: 'File name not provided'].
    fileName := args at: flagIndex + 2.

    countThreshold := args last asNumber ifNil: [self error: 'Threshold value not provided'].
    operation := args at: args size - 2.
    conditionValue := args last.

    "Read employee data from file"
    employees := self readFrom: fileName.

    "Perform operation"
    operation = 'count' ifTrue: [
        conditionOp := args at: args size - 1.
        result := self countEmployees: employees operation: operation conditionOp: conditionOp threshold: countThreshold value: conditionValue.
        'Number of employees satisfying condition: ', result asString displayNL.
    ] ifFalse: [self error: 'Unsupported operation'].
]     



    PayrollSystem >> countEmployees: employees operation: operation conditionOp: conditionOp threshold: threshold value: value [
        | count |

        count := 0.
        employees do: [:employee |
            | earnings |

            earnings := employee getEarning.

            (self check: earnings op: conditionOp threshold: threshold) ifTrue: [
                count := count + 1.
            ].
        ].
        ^ count.
    ]
].
