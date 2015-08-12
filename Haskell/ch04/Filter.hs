#! /usr/bin/env runhugs +l
--
-- Filter.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--


-- file: ch04/Filter.hs
oddList :: [Int] -> [Int]

oddList (x:xs) | odd x     = x : oddList xs
               | otherwise = oddList xs
oddList _                  = []


