import Control.Monad.Reader
import Control.Monad.Writer
import Control.Monad.State

data MyContext = MyContext
  { foo :: String
  , bar :: Int
  } deriving (Show)

computation :: Reader MyContext (Maybe String)
computation = do
  n <- asks bar
  x <- asks foo
  if n > 0
    then return (Just x)
    else return Nothing

ex1 :: Maybe String
ex1 = runReader computation $ MyContext "hello" 1

ex2 :: Maybe String
ex2 = runReader computation $ MyContext "haskell" 0


type MyWriter = Writer [Int] String

example :: MyWriter
example  = do
  tell [1..5]
  tell [5..10]
  return "foo"

output :: (String, [Int])
output = runWriter example

test :: State Int Int
test = do
  put 3
  modify (+1)
  get

outputState = execState test 0
