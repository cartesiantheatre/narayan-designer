/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Example unit rule using an agent and a transport handler from GlassBox engine
//  notes...
unitRule producePower

    // Test execution every 16 simulation ticks...
    rate 16

    // When you are ready to run, run but once...
    applyCount 1

    // Consume some coal...
    local Coal in 10

    // Produce some power and hand it over to an agent...
    agent Power out 10

    // Add pollution to pollution map...
    map AirPollution out 100

    // Send agent off to PowerConsumer sink via the PowerTransport...
    options -sendTo PowerConsumer -via PowerTransport

    // On success play a power sound...
    successEvent audio play_power_output

end

