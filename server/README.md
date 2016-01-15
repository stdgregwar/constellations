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
	output	uid : Int
	rules	uid == 0 if nick refused

MatchRequest
	input	gameStyle : String, localPlayerCount : Int, totalPlayerCount : Int, desiredPlayers : String 
	output	finalgameStyle : String
	rules   finalgamestyle is set to best fitting style or "error" if no match was found
	rules	desiredPlayers is empty => random match else => contains comma separated nicks of desired opponents

-Match preparation phase

NewPlayer
	bcast playerSlot : Int, playerUID: Int, playerNick : String, hatID : Int

PlayerLeave
	bcast playerSlot : Int

HatChange
	input 	hatID: Int
	bcast 	uid : Int, hatID: Int

LeavePool
	input 	wantToLeave : Boolean
	bcast 	uid : Int, leave : Boolean

RunTaunt
	input 	tauntID : String
	bcast 	tauntID : String

ReadyToGo
	input 	setReady : Boolean
	bcast 	uid : Int, ready : Boolean

CountDown
	bcast 	secToStart : Int
	rules 	send remaining sec to match start each sec

-Match Launch phase

MatchCanceled
	bcast	error : String

MatchStartHandshake
	bcast 	-
	input 	ready : Bool

MatchData
	bcast 	mapID : Int

```

Then the clients start to send binary action that are directly forwarded to other clients.

## Match

Todo
