### Client-server communication protocol

## Main connexion and match making

This part of the communication uses json to send messages to the server.

## Messages

Basic message struct :

```
Message
	input	kind: String, message: Action
	output	kind: String, message: Result
	bcast 	kind: String, message: Result
	rules	output and bcast behaviour
```

### Matchmaking Messsages

```
-Request phase

ConnectionRequest
	input	nick : String
	output	finalNick : String
	rules 	finalNick empty if connection refused
	
MatchRequest
	input	gameStyle : String, localPlayerCount : Int, totalPlayerCount : Int, desiredPlayers : List[String], mapID : Int
	output	finalGameStyle : String, playersSlots : List[Int], mapID : Int
	rules   finalGamestyle is set to best fitting style or "error" if no match was found
	rules	desiredPlayers is empty => random match else => contains comma separated nicks of desired opponents
	rules 	playersSlots contain slots assigned to local players

-Match preparation phase

NewPlayer
	bcast playerSlot : Int, playerNick : String

HatChange
	input 	hatID: Int, playerSlot : Int
	bcast 	hatID: Int, playerSlot : Int

RunTaunt
	input 	tauntID : String, playerSlot : Int
	bcast 	tauntID : String, playerSlot : Int

Status
	input 	ready : Boolean, playerSlot : Int
	bcast 	ready : Boolean, playerSlot : Int

LeaveNotification
	input 	-
	
PlayerLeave
	bcast playerSlot : Int

CountDown
	bcast 	secToStart : Int 
	rules 	send remaining sec to match start each sec

-Match Launch phase

MatchCanceled
	bcast	error : String

MatchStart
	bcast 	masterSlot : Int

```

Then the clients start to send binary action that are directly forwarded to other clients.

## Match

´´´
MatchEnd
	input -
´´´
