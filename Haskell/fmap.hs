#! /usr/bin/env runhugs +l
--
-- fmap.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--


import Data.Char  
import Data.List  
  
main = do line <- fmap (intersperse '-' . reverse . map toUpper) getLine  
          putStrLn line
