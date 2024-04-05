Object subclass: CommissionEmployee [
    | salesAmount commissionRate minWeeklyPay |

    CommissionEmployee class >> newWith: aFirstName and: aLastName and: aMinWeeklyPay and: aSalesAmount and: aCommissionRate [
        ^super new initWith: aFirstName and: aLastName and: aMinWeeklyPay and: aSalesAmount and: aCommissionRate
    ]

    CommissionEmployee >> initWith: aFirstName and: aLastName and: aMinWeeklyPay and: aSalesAmount and: aCommissionRate [
        minWeeklyPay := aMinWeeklyPay.
        salesAmount := aSalesAmount.
        commissionRate := aCommissionRate.
        ^super initWith: aFirstName and: aLastName
    ]

    CommissionEmployee >> getEarning [
        | commission |
        commission := salesAmount * commissionRate.
        ^commission max: minWeeklyPay
    ]
]

