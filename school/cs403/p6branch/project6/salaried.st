Object subclass: SalariedEmployee [
    | weeklySalary |

    SalariedEmployee class >> newWith: aFirstName and: aLastName and: aWeeklySalary [
        ^super new initWith: aFirstName and: aLastName and: aWeeklySalary
    ]

    SalariedEmployee >> initWith: aFirstName and: aLastName and: aWeeklySalary [
        weeklySalary := aWeeklySalary.
        ^super initWith: aFirstName and: aLastName
    ]

    SalariedEmployee >> getEarning [
        ^weeklySalary
    ]
]

