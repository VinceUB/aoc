import unittest

from part1 import *

class MapTest(unittest.TestCase):
    def test_apply(self):
        m = Map("50 98 2\n")

        self.assertEqual(m.dest_start, 50)
        self.assertEqual(m.source_start, 98)
        self.assertEqual(m.range_length, 2)
        
        self.assertEqual(m.apply( 97), (False, 97))
        self.assertEqual(m.apply( 98), (True, 50))
        self.assertEqual(m.apply( 99), (True, 51))
        self.assertEqual(m.apply(100), (False, 100))

if __name__ == '__main__':
    unittest.main()
