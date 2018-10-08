/// <summary>
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