# -*- coding: utf-8 -*-

def demo1():
    try:
        raise RuntimeError,"To Force Issue"
    except:
        return 1
    else:
        return 2
    finally:
        print "haha"
        #return 3

def demo2():
    try:
        try:
            raise RuntimeError,"To Force Issue"
        except:
            return 1
        else:
            return 2
        finally:
            return 3
    except:
        print 4
    else:
        print 5
    finally:
        print 6

if __name__ == "__main__":
    print "*** DEMO ONE ***"
    print demo1()
    print "****************"
    print 
    print "*** DEMO TWO ***"
    print demo2()
    print "****************"
    for i in xrange(4):
        print i
    print i
