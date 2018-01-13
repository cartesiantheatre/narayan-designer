/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Example unit rule with a chaining effect to create mustard from GlassBox
//  engine notes...
unitRule mustardFactory

    // Test execution every 10 simulation ticks...
    rate 10

    // Consume some money from global bin...
    global Simoleans in 1

    // Consume mustard and an empty bottle...
    local YellowMustard in 6
    local EmptyBottle in 1

    // Produce one bottle of yellow mustard...
    local BottleOfMustard out 1

    // Add pollution to pollution map...
    map Pollution out 5

    // On success show an animation and play a factory sound...
    successEvent effect smokePuff
    successEvent audio  chugAndSlurp

    // Otherwise execute another rule on failure...
    onFail buyMoreMustard

end

