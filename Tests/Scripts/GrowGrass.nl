// Map rule for growing grass...
mapRule growGrass

    // Test execution every 200 simulation ticks...
    rate 200

    // Soil map needs enough soil...
    test map Soil atLeast 20

    // Consume water and nutrients from water and nutrient maps...
    map Water in 10
    map Nutrients in 1

    /* If everything above was ok, grow the grass a bit...*/
    map Grass out 5

end

