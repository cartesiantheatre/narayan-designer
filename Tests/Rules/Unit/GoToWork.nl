/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Example unit rule emitting an agent from GlassBox engine notes...
unitRule goToWork

    // Send agent to either work or the park, then home, and repeat after 10
    //  by a car on the road...
    options -sendTo Work -or Park -switchTo Home 10 -repeatAfter 10 -via Car -using Road

    // Need to have at least two people...
    local People in 2

    // Transfer people into agent...
    agent People out 2

end

