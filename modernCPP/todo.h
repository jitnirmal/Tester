/// <summary>
/// https://herbsutter.com/2013/05/29/gotw-89-solution-smart-pointers/
/// 
/// 
/// https://herbsutter.com/welcome-to-the-jungle/
/// a. Unified : Every pointer (or object reference) can address every byte, and every byte is equally “far away” from the core.
///					-- locality
///					-- how well “hot” data fits into cache
///       NUMA : retains a single chunk of RAM, but adds multiple caches
///					-- two cores that share an L2 cache vs. two cores that share only L3 or RAM
///					-- layout matters,  on the same cache line because we have to keep data physically close together if it’s used together
///					--  to avoid the ping-pong game of false sharing
/// b. Morre law
/// 
/// </summary>
/// 

/// <summary>
/// FIX
///		-- messaging standard for the electronic exchange 
///				-- to distribute market data, quotes, etc.
///				-- to send orders to markets
///				-- Transport independent
/// Message sections
///		Header fields - message type, length, sequence number, sender / target, encoding, etc.
///		Body fields - session & application data
///		Trailer fields - Signature, checksum
/// Session level msgs : Logon, Heartbeat, Sequence Reset, Logout
/// Application level msgs : 100+ 
///		 New order – single
///		 Execution report
///		 Order cancel/replace request
///		 Order cancel request
///		 Allocation
///		Confirmation
/// Tag=Value syntax : 4 components to each field
///					<Tag >= <Value><Delimiter>, <Delimiter> is ASCII SOH character
/// Cleint connects TCP socket to predefined port on sell side FIX Engine.Server accepts TCP connection.
///			Cleint sends a Logon msg.Server sends a Logon msg back.
///			Client sends New Order – Single msg.
///			Server side sends Execution Rpt acknowledging order
///			Server side sends Execution Rpt containing fill.
/// 8=FIX.4.2^9=251^35=D^49=AFUNDMGR^56=ABROKER^34=2^ 52=20030615-01:14:49^11=12345^21=1^ 55=IBM^54=1^ 60=2003061501:14:49^38=5000^40=2^44=110.75^10=127 
/// Header fields:
///		8 = BeginString(indicates FIX 4.2)
///		9 = BodyLength
///		35 = MsgType(new order)
///		49 = SenderCompID(AFUNDMGR)
///		56 = TargetCompID(ABROKER)
///		34 = MsgSeqNum(2)
///		52 = SendTime
/// Body fields:
///		11 = ClOrderID(client order id)
///		21 = HandleInst(automated exec)
///		55 = Symbol(IBM)
///		54 = Side(buy)
///		56 = TransactTime
///		38 = OrderQty(5000)
///		40 = OrdType(Limit)
///		44 = Price(110.75)
///		52 = SendTime
/// Trailer Fields:
///		10 = Checksum
/// 
/// 
/// ExecType (150) : type of execution report received
/// OrdStatus (39) : indicates the current status of the order
/// SecurityType (167) : equity , future, options
/// HandlInst (21) =3 (manual)Care order
///  Rule80A (47) 
/// FIX tag 8 : Fix version
/// 
/// OrderCancelReplaceRequest (tag 35=F) 
/// NewOrderSingle (35=A)













/// </summary>

