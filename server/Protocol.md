### Client-server communication protocol

## Main connexion and match making

This part of the communication uses json to send messages to the server.

## Messages

Basic message struct :

```
Message
	input	kind: String, message: Action, metadata: Metadata
	output	(1) kind: String, message: Result, metadata: Metadata
	output	(2) message: String, metadata: Metadata
	rules	success (1) | error (2)
	bcast	kind: String, message: Result, metadata: Metadata
```

