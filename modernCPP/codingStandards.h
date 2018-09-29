#include <cstddef>
#include <vector>

/// <summary>
/// 1. Use your compiler's highest warning level. Eliminate warnings by changing your code, not by reducing the warning level.
/// 2. Use an automated build system - as you don't have time and energy to waste on something that can be automated.
/// 3. Invest in code reviews
/// 		-- Increase code quality through beneficial peer pressure.
///			-- Find bugs and potential scaling problems.
///			-- Foster better design and implementation through cross - breeding of ideas.
///         -- Bring newer teammates and beginners up to speed.
///			-- Increase confidence and professional pride.
/// 4. Care for scalability, recovery, performance
/// 5. Don't optimize prematurely and everything
/// 6. Use explicit RAII and smart pointers
/// 7. Use const proactively
/// </summary>
/// 


// disable warning
#pragma warning(push) //disable for this header only
#pragma warning(disable:4512)
#pragma warning(disable:4180)
#include <boost/lambda/lambda.hpp> 
#pragma warning(pop) //restore original warning level