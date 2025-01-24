# Notes

## Pointers + offset

From the "current screen" static address (0x13FFF0000 on Windows and 0x15DCD9415? on Linux):

- current club is + 0x18
- current person is + 0x68
- current player is + 0x70
- current staff member is + 0x80
- current team is + 0x88

## Mapping person

- 0x08 = Row ID
- 0x0C = Unique ID
- 0x10 = Random ID
- 0x44 = Date of birth (2 bytes for day of the year, 2 bytes for year)
- 0x48 = Full name pointer (+0x04 from here)
- 0x58 = Forename pointer (+0x04 from here)
- 0x60 = Surname pointer (+0x04 from here)
- 0x78 = Adaptability
- 0x79 = Ambition
- 0x7A = Loyalty
- 0x7B = Pressure
- 0x7C = Professionalism
- 0x7D = Sportsmanship
- 0x7E = Temperament
- 0x7F = Controversy
- 0x80 = Relationship start/end pointer (0x00 from here is start, 0x08 from here is end)
- 0xC8 = Contract pointer

## Mapping player

- 0xF8 = Injury start/end pointer (0x00 from here is start, 0x08 from here is end)
- 0x1D0 = Guide value
- 0x1D4 = Transfer value
- 0x1F4 = Sharpness
- 0x1F6 = Fatigue (0 is best)
- 0x1F8 = Condition
- 0x1FA = Home reputation
- 0x1FC = Current reputation
- 0x1FE = World reputation
- 0x200 = Current ability
- 0x202 = Potential ability
- 0x266 = Preferred position
	- 0x01 = right
	- 0x02 = left
	- 0x03 = right/central
	- 0x04 = left/central
	- 0x05 = central
	- 0x06 = right when 2, right/central
- 0x328 = function call run when jadedness changes?

## Mapping staff

- 0x18 - 0x1B = attributes?
- 0x1C = Level of discipline
- 0x1D - 0x23 = attributes?
- 0x24 = Working with youngsters
- 0x25 = Determination
- 0x16 - 0x31 = attributes?
- 0x32 = Coaching player
- 0x33 = coaching GK shot stopping
- 0x34 = Judging CA
- 0x35 = Judging PA
- 0x36 = Man management
- 0x37 = Motivating
- 0x38 = Physiotherapy
- 0x39 = Tactical knowledge
- 0x3A = Coaching attacking
- 0x3B = Coaching defending
- 0x3C = Coaching fitness
- 0x3D = Coaching mental attributes
- 0x3E = Coaching technical
- 0x3F = Coaching tactical/non-tactical
- 0x40 = Coaching dirtiness allowance
- 0x41 = Coaching GK handling
- 0x42 = Coaching GK distribution
- 0x43 = Versatility
- 0x44 - 0x46 = attributes?
- 0x47 = Sports science
- 0x49 = Negotiating
- 0x4A = Judging staff ability
- 0x4B = Judging staff ability
- 0x58 = Pointer to some dates? 2023-2025?
- 0xD6 = CA
- 0xD8 = PA

## Mapping contract

- 0x08 = Person pointer
- 0x10 = Club pointer
- 0x18 = Weekly wage
- 0x1C = Job (1 = player, 2 = coach, 3 = player/coach)
- 0x30 = Loyalty bonus
- 0x3C = Start date
- 0x40 = End date
- 0x9C = Agent fees?
- 0xB4 = Contract type (0 is part-time, 1 is full time, 2 is amateur, 3 is youth, 4 is non-contract)

## Mapping club

- 0x08 = Row ID
- 0x0C = Unique ID
- 0x10 = Random ID
- 0x30 = Name/teams? pointer

## Mapping Team

The whole object is 0xB8 bytes long

- 0x05 = always 1?
- 0x08 = Row ID
- 0x0C = Unique ID
- 0x10 = Random ID
- 0x28 = Team type (0 for first team, 1 for reserves, 0x0C for U18, 0x16 for youth intake)
- 0x29 = 0 for senior, else always 1?
- 0x30 = Name/teams? pointer
- 0x38 = Pointer to start of players
- 0x40 = Pointer to end of players
- 0xA8 = Reputation

## Mapping name/teams?

- 0x18 = squad list pointer
- 0xC0 = long name (+ 0x04 from here)
- 0xC8 = short name (+ 0x04 from here)

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

## Mapping relationships

These offsets are for each individual relationship

- 0x00 = relationship target (club or person) (if applicable)
- 0x09 = person type (if relationship is about with a person)
	- 0x00 = None
	- 0x01 = parent
	- 0x02 = sibling
	- 0x03 = child
	- 0x04 = relation
	- 0x05 = teammate
	- 0x06 = manager
	- 0x07 = player
	- 0x08 = backroom staff
	- 0x09 = idol
	- 0x0A = friend
	- 0x0B = youth staff
- 0x0B = ??
- 0x0C = type
	- 0x01 = likes person
	- 0x02 = dislikes person
	- 0x03 = likes team
	- 0x04 = dislikes team
	- 0x09 = other nationality
	- 0x0A = international retirement
	- 0x48 = training happiness
	- 0x48 = formed at club
- 0x0D = relationship value (if applicable)

## Date & time

- Day is represented with 1 byte and a 1 bit in the following byte to represent values > 255
- Time is represented as 1 byte (even bits only) determining the number of 15 minute periods since 6AM  
  (plus 1 because 0 is midnight)
- Year is 2 bytes

e.g. Sunday 12th of May, 2024 at 0800 is `85 12 E8 07`

## Supporter profile

Search for profile distribution as byte array. e.g. `0D 22 17 0C 00 12` representing 13, 34, 23, 12, 0, 18.

- 0x00 social media followers
- 0x0E hardcore distribution
- 0x0F core distribution
- 0x10 family distribution
- 0x11 fair weather distribution
- 0x12 corporate distribution
- 0x13 casual distribution
- 0x1C supporter loyalty
- 0x1D supporter passion
- 0x1E supporter patience
- 0x1F supporter affluence
- 0x20 supporter temperament
- 0x21 supporter expectations
