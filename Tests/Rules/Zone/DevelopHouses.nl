/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Example zone rule for developing houses in well defined areas. Taken from the
//  GlassBox engine notes...
zoneRule developHouses

    // Execute every half a day...
    timeTrigger Day 0.5

    // Develop three houses a day...
    sample random -count 3

    // But only if there are enough builders available...
    global Builders atLeast 5

    // ...and only if you can actually build here...
    map Forest is 0

    // Go ahead and create the new units...
    createUnit -id Bungalows

end

