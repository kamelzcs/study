#! /usr/bin/env runhugs +l
--
-- Sum.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--


-- file: ch04/Sum.hs
mySum xs = helper 0 xs
    where helper acc (x:xs) = helper (acc + x) xs
          helper acc _      = acc

niceSum :: [Integer] -> Integer
niceSum xs = foldl (+) 0 xs
