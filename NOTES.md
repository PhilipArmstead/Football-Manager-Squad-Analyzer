# Notes

## Pointers + offset

From the "current screen" static address (0x13FFF0000 on Windows and 0x15DCD9415? on Linux):

- current club is + 0x18
- current person is + 0x68
- current player is + 0x70
- current staff member is + 0x80
- current team is + 0x88

## Mapping Team

- Row ID is +0x08
- Unique ID is +0x0C
- Random ID is +0x10
- Team type is +0x28 (0 for first team, 1 for reserves, 0x0C for U18)
- Pointer to array of players(??) is +0x38
- Pointer to end of array of players(??) is +0x40
- Reputation is +0xA8

## Mapping person

- Row ID is + 0x08
- Unique ID is + 0x0C
- Random ID is + 0x10
- Date of birth is + 0x44 (2 bytes for day of the year, 2 bytes for year)

## Mapping player

- Guide value is +0x1D0
- Transfer value is +0x1D4
- Sharpness is +0x1F4 (2 bytes)
- Fatigue is +0x1F6 (signed 2 bytes (0 is best))
- Condition is +0x1F8 (2 bytes)
- Home reputation is +0x1FA (2 bytes)
- Current reputation is +0x1FC (2 bytes)
- World reputation is +0x1FE (2 bytes)
- CA is +0x200
- PA is +0x202
- Preferred position is +0x266 (1=right,2=left,3=right/central,4=left/central,5=central,6=right when 2,right/central)

## Mapping contract

- Job is +0x1C (1 = player, 2 = coach, 3 = player/coach)
- Weekly wage is +0x18
- Loyalty bonus is +0x98
- Agent fees is +0x9C
- Start date is +0x3C
- End date is +0x40
- Contract type is +0xB4 (0 is part time, 1 is full time, 2 is amateur, 3 is youth, 4 is non-contract)

## Mapping attributes

- -0x78 = CA
- -0x76 = PA
- -0x70 = position start (GK)
- -0x6F = Sweeper (unused?)
- -0x6E = DL
- -0x6D = DC
- -0x6C = DR
- -0x6B = DM
- -0x6A = ML
- -0x69 = MC
- -0x68 = MR
- -0x67 = AML
- -0x66 = AMC
- -0x65 = AMR
- -0x64 = ST
- -0x63 = WBL
- -0x62 = WBR
- -0x61 = Crossing
- -0x60 = Dribbling
- -0x5F = Finishing
- -0x5E = Heading
- -0x5D = Long shots
- -0x5C = Marking
- -0x5B = Off the Ball
- -0x5A = Passing
- -0x59 = Penalty
- -0x58 = Tackling
- -0x57 = Vision
- -0x56 = Handling
- -0x55 = Aerial Ability
- -0x54 = Command of Area
- -0x53 = Communication
- -0x52 = Kicking
- -0x51 = Throwing
- -0x50 = Anticipation
- -0x4F = Decisions
- -0x4E = One on Ones
- -0x4D = Positioning
- -0x4C = Reflexes
- -0x4B = First Touch
- -0x4A = Technique
- -0x49 = Left foot
- -0x48 = Right foot
- -0x47 = Flair
- -0x46 = Corners
- -0x45 = Teamwork
- -0x44 = Work Rate
- -0x43 = Long Throws
- -0x42 = Eccentricity
- -0x41 = Rushing Out
- -0x40 = Tendency to Punch
- -0x3F = Acceleration
- -0x3E = Free Kick Taking
- -0x3D = Strength
- -0x3C = Stamina
- -0x3B = Pace
- -0x3A = Jumping Reach
- -0x39 = Leadership
- -0x38 = Dirtiness
- -0x37 = Balance
- -0x36 = Bravery
- -0x35 = Consistency
- -0x34 = Aggression
- -0x33 = Agility
- -0x32 = Important Matches
- -0x31 = Injury Proneness
- -0x30 = Versatility
- -0x2F = Natural Fitness
- -0x2E = Determination
- -0x2D = Composure
- -0x2C = Concentration
- 0 = base
- +0x0C = Random ID
- +0x10 = UID
- +0x78 = Adaptability
- +0x79 = Ambition
- +0x7A = Loyalty
- +0x7B = Pressure
- +0x7C = Professionalism
- +0x7D = Sportsmanship
- +0x7E = Temperament
- +0x7F = Controversy

## Date & time

- Day is represented with 1 byte and a 1 bit in the following byte to represent values > 255
- Time is represented as 1 byte (even bits only) determining the number of 15 minute periods since 6AM  
  (plus 1 because 0 is midnight)
- Year is 2 bytes

e.g. Sunday 12th of May, 2024 at 0800 is `85 12 E8 07`
