#! /usr/bin/env runhugs +l
--
-- Main.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--

module Main where

import SimpleJSON
import PutJSON

main = putJValue (JObject [("foo", JNumber 1), ("bar", JBool False)])
