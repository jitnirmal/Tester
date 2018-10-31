/// <summary>
/// 100 GOLD COINS
/// There are 5 pirates, they must decide how to distribute 100 gold coins among them. 
/// The pirates have seniority levels, the senior-most is A, then B, then C, then D, and finally the junior-most is E.
/// Rules of distribution are :
/// The most senior pirate proposes a distribution of coins.
/// All pirates vote on whether to accept the distribution.
/// If the distribution is accepted, the coins are disbursed and the game ends.
/// If not, the proposer is thrown and dies, and the next most senior pirate makes a new proposal to begin the system again.
/// In case of a tie vote the proposer can has the casting vote
/// Rules every pirates follows.
/// 
/// Solutions:
/// The answer is 98 which is not intuitive.A uses below facts to get 98.
/// Consider the situation when A, B and C die, only D and E are left.E knows that he will not get anything(D is senior and
///  will make a distribution of(100, 0).So E would be find with anything greater than 0.
/// Consider the situation when A and B die, C, D and E are left.
/// D knows that he will not get anything(C will make a distribution of(99, 0, 1) and E will vote in favor of C).
/// Consider the situation when A dies.B, C, D and E are left.To survive, B only needs to give 1 coin to D.So distribution is(99, 0, 1, 0)
/// Similarly A knows about point 3, so he just needs to give 1 coin to C and 1 coin to E to get them in favor.So distribution is(98, 0, 1, 0, 1).
/// The idea is based on the fact that what B will distribute if A dies(B would always want A to die).If A gives more coins to 2 people than B would have given, A wins.
/// </summary>
/// ----------------------------------------------------------------------------------------------------------------------------------------------------------------
/// Puzzle 2 | (Find ages of daughters)
/// Alok has three daughters.His friend Shyam wants to know the ages of his daughters.Alok gives him first hint.
/// 1) The product of their ages is 72.
/// 2) The sum of their ages is equal to my house number.
/// Shyam goes out and look at the house number and tells “I still do not have enough information to determine the ages”.
/// 3) The oldest of the girls likes strawberry ice-cream.
/// Shyam is able to guess after the third hint.Can you guess what are the ages of three daughters ?
/// ----------------------------------------------------------------------------------------------------------------------------------------------------------------
/// Puzzle 3 | (Calculate total distance travelled by bee)
/// Two trains are on same track and they are coming toward each other. 
/// The speed of first train is 50 KMs/h and the speed of second train is 70 KMs/h. A bee starts flying between the trains 
/// when the distance between two trains is 100 KMs. The bee first flies from first train to second train.
///  Once it reaches the second train, it immediately flies back to the second train … and so on until trains collide. 
/// Calculate the total distance traveled by the bee. Speed of bee is 80 KMs/h.
/// 
/// Solution : Let the first train moves at u km/h, second train moves at v km / h, distance betweem trains be d km, time taken by trains to collide = d/(u+v)
/// distance travelled by bee = b*d/(u+v) = 80 * 100/(50+70) = 66.67(approx.)
/// ----------------------------------------------------------------------------------------------------------------------------------------------------------------
/// 
/// 
/// 
/// What are three strengths that you bring to this position?
/// 
/// How do you deal with conflict? (conflict averse or solution oriented)
/// -- Talking to person : setting up meeting or lunch session, understanding his/her viewpoint.
///		-- sometime you need to agree on disagreements
///		-- in general avoid blames
/// 
/// 
/// Do you consider yourself lucky ? (cocky or humble)
/// How was your commute to the interview ? (complainer or no worries)
/// What kind of people do you not like working with ? (do they bring up their boss)
/// 
/// I am passionate for building up world class results
/// 
/// I see myself on the path of hands on programmer
/// 
/// Conflict;
///		Conflict wrt work delivery :
///		Conflict on the quality of code :
/// 
/// 
///		System Architecture, design, development, testing and production rollout – trading, pricing and risk engines.
///				1.	Regulatory requirements for global markets(trading patterns, price and position checks, market depth), safety control, throttle,
///				2.	replacement of 3rd party risk engine
///				3.	re - architecture of platform
///						a.performance / latency
///						b.stability of platform
///						c.capacity, resiliency, recovery
///				4.	platform performance, optimized for low latency clients – sub micro
///				5.	Implementation of position based smart order routing
///				7.	different asset classes - equities and listed derivative space.
///				8.	Tools for user interface providing real - time views for risk and position portfolio
///				9.	Google test, test automation, parallel production runs
///				10. product quality
///						- requirement JIRA, 
///						- Clang tidy (static analysis) - modern cpp, performance, memory
///						- valgrind, vtune, gprof
///						- team city for build integration 

/// 
/// How would your friend describe you.
///   -- energetic, dedicated, result oriented 
/// 
/// Strengths
///		-- broad technical experience - and sound business understanding can provide client focused solutions
///			(multiple object oriented languages, low and standard latency, trading, pricing and risk engines)
///		-- result oriented
///			(delivered complex project, with high quality and within time constraints)
///		-- team player 
///			(lead, mentor, peer/ worked with Market, Product, Price and several client team. Good confidence of getting the work done.)
///		-- positive attitude 
///			(inovations - chatbot, ELK server(hackathon), simulation service)
/// 
/// Weekness 
///		-- Masters for business kowledge
///		-- pressure handling
/// 
/// Projects
///		-- 
/// 
/// Team Structure
///		-- 5 developers including myself (2 Pune, 2 Singapore and 1 London)
///		-- 3 BAU support persons.
/// 
/// What is your greatest accomplishment or the project you’re most proud of completing? 
/// Although lots of technical enhancement and functional deliveries, but thing really put in challenge was
///  MLRM (FX)
///		-- resources
///		-- technology challenges 
///				-- define the integrtion points for position feed (with 7 client application)
///						-- discussion, coordination, planning/ api design and position check approach
///						-- need to be low latency (which in some sytem we can understand after testing)
///						-- solution - parallel run, agora based back testing
///		-- existing issues in the other application
///				-- detailed deep analysis, proactively identifying them (fail fast)
///				-- working with them for fixes (discussed with client application)	
///				-- biweekly call with senior management to get their attention, feedback
///		-- strict timelines
///				-- conservative plans, team was committed for the delivery (lead role)
///		-- praise
/// 
/// 
/// 
///  
/// If you had to live your life over again, what one thing would you change?
/// 
/// “Tell me about a time when you took the lead on a difficult project?”
/// 
/// “Describe a Situation Where You Disagreed With a Supervisor.” 
///		-- Though it is rare as he has confidence on my approach and provide me resonable freedom.
///			Generally it happens in terms of a) delivery timelines, b) reschuffling priorities.
///			- sorted by discussion.
/// 
///	
///  -- Good place to learn and grow	
///	 -- flat structure, individual contribution is valued
///  -- lot of talented people under the same roof 
/// 
