/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Example map rule for growing grass from GlassBox engine notes...
mapRule growGrass

    // Test execution every 200 simulation ticks...
    rate 200

    // Soil map needs enough soil...
    map Soil atLeast 20
    
    // Consume water and nutrients from water and nutrient maps...
    map Water in 10
    map Nutrients in 1

    /* If everything above was ok, grow the grass a bit...*/
    map Grass out 5

end

