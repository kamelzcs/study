#! /usr/bin/env runhugs +l
--
-- Fold.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--


-- file: ch04/Fold.hs
myFilter p xs = foldr step [] xs
    where step x ys | p x       = x : ys
                    | otherwise = ys

myMap :: (a -> b) -> [a] -> [b]

myMap f xs = foldr step [] xs
    where step x ys = f x : ys

myFoldl :: (a -> b -> a) -> a -> [b] -> a

myFoldl f z xs = foldr step id xs z
    where step x g a = g (f a x)
