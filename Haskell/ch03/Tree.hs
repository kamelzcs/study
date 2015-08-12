#! /usr/bin/env runhugs +l
--
-- Tree.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--

-- file: ch03/Tree.hs
data Tree a = Node a (Tree a) (Tree a)
            | Empty
              deriving (Show)


