#! /usr/bin/env runhugs +l
--
-- ListADT.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--

data List a = Cons a (List a)
            | Nil
              deriving (Show)


