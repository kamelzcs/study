--
-- A.hs
-- Copyright (C) 2015 zhao <zhao@kamel-Desktop>
--
-- Distributed under terms of the MIT license.
--

import qualified System.IO
import Control.Monad
import Control.Applicative
import Text.Printf
import Data.Char (digitToInt)
import Data.List (foldl', sort)
import Data.Bits
import Data.Int

toDec :: String -> Int64
toDec = foldl' (\acc x -> acc * 2 + (fromIntegral $ digitToInt x ::Int64)) 0

minimum' :: (Ord a) => [a] -> Maybe a
minimum' x
    | x == [] = Nothing
    | otherwise = Just $ minimum x

gcj solver =
  System.IO.hSetBuffering System.IO.stdout System.IO.NoBuffering >>
  readLn >>= sequence_ . flip take [solver >>= output num | num <- [1..]] where
    output num ans = putStrLn $ "Case #"++show num++": "++ans

main :: IO ()
main = gcj $ do
    _ <- getLine
    a <- map toDec . words <$> getLine
    b <- sort . map toDec . words <$> getLine
    let valid x = sort (map (`xor` x) a) == b
        d = filter valid $ map (\ x -> xor x (head a)) b
    return . maybe "NOT POSSIBLE" show $ minimum' $ map popCount d
