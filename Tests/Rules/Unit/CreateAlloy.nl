/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Example unit rule to create an allow from raw ore from GlassBox engine
//  notes...
unitRule createAlloy

    // Test execution every 2 simulation ticks...
    rate 2

    // When you are ready to run, run but once...
    applyCount 1

    // Consume raw ore...
    local Ore in 10

    // Produce alloy...
    local Alloy out 15

    // Add pollution to the air pollution map...
    map AirPollution out 100

    // Show pollution animation if successful...
    successEvent effect pollute

    // Otherwise show alert in engine user interface on fail...
    failEvent alert out_of_resources

end

