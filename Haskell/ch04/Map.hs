#! /usr/bin/env runhugs +l
--
-- Map.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--

-- file: ch04/Map.hs
square2 xs = map squareOne xs
    where squareOne x = x * x

upperCase2 xs = map toUpper xs


