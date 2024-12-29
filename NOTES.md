# Notes

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

## Memory view

```
0x3E4DA568: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA578: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA588: 01 00 00 00 01 00 6C 07 01 00 6C 07 01 00 6C 07
0x3E4DA598: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA5A8: 00 00 00 00 00 00 10 00 0C 00 FF 28 20 9C 9C 32
0x3E4DA5B8: 25 32 32 32 1B 05 00 00 8B 97 E6 00 FF FF FF FF
0x3E4DA5C8: 9B 03 00 00 FF FF FF FF FF FF FF FF FF FF FF FF
0x3E4DA5D8: 00 00 00 00 8E 00 E7 07 01 00 6C 07 3E 17 83 FF
0x3E4DA5E8: 10 27 00 19 00 19 00 19 C8 00 C8 00 00 00 00 00
0x3E4DA5F8: 01 01 01 01 01 01 01 01 01 01 01 01 14 01 01 58
0x3E4DA608: 58 58 58 58 58 58 58 58 58 58 05 05 05 05 05 05
0x3E4DA618: 58 58 05 58 05 58 58 05 64 64 58 58 58 58 05 05
0x3E4DA628: 05 58 58 58 58 58 58 5F 23 58 5F 64 1E 58 64 14
0x3E4DA638: 64 64 64 58 58 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA648: 00 00 00 55 FF C8 C8 0B 00 0C FF 05 B0 C8 00 FF
0x3E4DA658: 00 14 0B 0A 00 00 00 00 00 00 00 00 00 00 00 00
base  A668: 78 EE A4 45 01 00 00 00 1E 28 00 00 4D BD 54 77
0x3E4DA678: 9D A5 13 0F 00 00 00 00 00 0A 60 10 00 00 00 00
0x3E4DA688: 00 00 00 00 00 00 00 00 28 EE A4 45 01 00 00 00
0x3E4DA698: 3C E9 A4 45 01 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA6A8: 8E 1A E7 07 B7 00 D0 07 00 00 00 00 00 00 00 00
0x3E4DA6B8: 00 00 00 00 00 00 00 00 00 D9 9B 33 00 00 00 00
0x3E4DA6C8: 20 1E C6 34 00 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA6D8: 08 12 E3 32 00 00 00 00 05 06 07 08 09 0A 0B 0C
0x3E4DA6E8: 80 D4 45 3E 00 00 00 00 50 3C DD 2F 00 00 00 00
0x3E4DA6F8: FF 00 01 01 FF 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA708: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA718: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA728: 00 00 00 00 00 00 00 00 E0 78 58 3E 00 00 00 00
0x3E4DA738: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA748: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x3E4DA758: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```

## Other stuff

0x172a6aa: current screen's name?

### Names

```
0x1736440 
0x41bf835
0x41bf985 
0x21f37f60
0x21f3c7aa
0x234eb6dc
0x25063c50
0x253abb3b
0x278d5e70
0x278d60f0
0x278dd530
0x51be3e05 <-- 0x29a1a335
```