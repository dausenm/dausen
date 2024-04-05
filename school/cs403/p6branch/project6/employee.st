Object subclass: Employee [
    | firstName lastName |

    Employee class >> new [
        ^super new
    ]

    Employee >> initWith: aFirstName and: aLastName [
        firstName := aFirstName.
        lastName := aLastName.
        ^self
    ]

    Employee >> getInfo [
        ^'Name: ', firstName, ' ', lastName
    ]

    Employee >> getEarning [
        "To be implemented by subclasses"
    ]
]

