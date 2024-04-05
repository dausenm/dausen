Object subclass: HourlyEmployee [
    | hourlyRate hoursWorked |

    HourlyEmployee class >> newWith: aFirstName and: aLastName and: anHourlyRate and: anHoursWorked [
        ^super new initWith: aFirstName and: aLastName and: anHourlyRate and: anHoursWorked
    ]

    HourlyEmployee >> initWith: aFirstName and: aLastName and: anHourlyRate and: anHoursWorked [
        hourlyRate := anHourlyRate.
        hoursWorked := anHoursWorked.
        ^super initWith: aFirstName and: aLastName
    ]

    HourlyEmployee >> getEarning [
        | overtimePay |
        overtimePay := 0.
        overtimePay := (hoursWorked - 40) max: 0 * 1.5 * hourlyRate.
        ^40 * hourlyRate + overtimePay
    ]
]

