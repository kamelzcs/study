#! /usr/bin/env runhugs +l
--
-- toupper-lazy4.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--

import Data.Char(toUpper)

main = interact (map toUpper)


