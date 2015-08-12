#! /usr/bin/env runhugs +l
--
-- Adler32.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--

-- file: ch04/Adler32.hs
--
import Data.Char (ord)
import Data.Bits (shiftL, (.&.), (.|.))
base = 65521

adler32_foldl xs = let (a, b) = foldl step (1, 0) xs
                   in (b `shiftL` 16) .|. a
    where step (a, b) x = let a' = a + (ord x .&. 0xff)
                          in (a' `mod` base, (a' + b) `mod` base)


