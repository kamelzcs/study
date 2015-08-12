#! /usr/bin/env runhugs +l
--
-- eqclasses.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--

class  Eq a  where
    (==), (/=) :: a -> a -> Bool

       -- Minimal complete definition:
       --     (==) or (/=)
    x /= y     =  not (x == y)
    x == y     =  not (x /= y)
