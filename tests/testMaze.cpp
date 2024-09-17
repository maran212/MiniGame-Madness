#include "pch.h"
#include "CppUnitTest.h"
#include "../src/maze.h"
#include <set>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MazeTests
{
    TEST_CLASS(MazeTests)
    {
    public:
        TEST_METHOD(TestIsValidPosition)
        {
            Maze maze(10, 10);
            Assert::IsTrue(maze.isValidPosition(std::make_pair(0,0)));
            Assert::IsTrue(maze.isValidPosition({ 9, 9 }));
            Assert::IsFalse(maze.isValidPosition({ -1, 0 }));
            Assert::IsFalse(maze.isValidPosition({ 0, -1 }));
            Assert::IsFalse(maze.isValidPosition({ 10, 0 }));
            Assert::IsFalse(maze.isValidPosition({ 0, 10 }));
        }

        TEST_METHOD(TestPickRandomDirection)
        {
            Maze maze(10, 10);
            std::vector<Direction> directions = { Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST };
            std::set<Direction> pickedDirections;

            for (int i = 0; i < 100; ++i)
            {
                pickedDirections.insert(maze.pickRandomDirection(directions));
            }

            // Verify that all 4 directions are picked
            Assert::IsTrue(pickedDirections.size() == 4);
        } 
        TEST_METHOD(TestGetOppositeDirection)
        {
            Maze maze(10, 10);;
			Assert::IsTrue(maze.getOppositeDirection(Direction::NORTH) == Direction::SOUTH);
			Assert::IsTrue(maze.getOppositeDirection(Direction::SOUTH) == Direction::NORTH);
			Assert::IsTrue(maze.getOppositeDirection(Direction::EAST) == Direction::WEST);
			Assert::IsTrue(maze.getOppositeDirection(Direction::WEST) == Direction::EAST);

			Assert::IsFalse(maze.getOppositeDirection(Direction::NORTH) == Direction::NORTH);
			Assert::IsFalse(maze.getOppositeDirection(Direction::SOUTH) == Direction::SOUTH);
			Assert::IsFalse(maze.getOppositeDirection(Direction::EAST) == Direction::EAST);
			Assert::IsFalse(maze.getOppositeDirection(Direction::WEST) == Direction::WEST);
        }

        TEST_METHOD(TestLinkNodes)
        {
            Maze maze(10, 10);
            maze.generateMaze(10, 10);

            std::pair<int, int> start = { 0, 0 };
            std::pair<int, int> end = { 0, 1 };
            if (maze.mazeMap.at(start)->getNeighbor(Direction::EAST) != nullptr) {
                maze.mazeMap.at(start)->removeNeighbor(Direction::EAST);
            }

			if (maze.mazeMap.at(end)->getNeighbor(Direction::WEST) != nullptr) {
				maze.mazeMap.at(end)->removeNeighbor(Direction::WEST);
			}
			
			maze.linkNodes(start, end);
            MazeNode* startNode = maze.mazeMap[start].get();
            MazeNode* endNode = maze.mazeMap[end].get();
            Assert::IsTrue(startNode->getNeighbor(Direction::EAST) == endNode);
            Assert::IsTrue(endNode->getNeighbor(Direction::WEST) == startNode);
        }

        TEST_METHOD(TestEraseLoop)
        {
            Maze maze(10, 10);
            std::vector<std::pair<int, int>> path = { {0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 1}, {0, 1} };
            std::vector<std::pair<int, int>> expectedPath = { {0, 0}, {0, 1} };
            std::vector<std::pair<int, int>> resultPath = maze.eraseLoop(path, { 0, 1 });
            // Log the resultPath
            for (const auto& position : resultPath) {
                Logger::WriteMessage(("(" + std::to_string(position.first) + ", " + std::to_string(position.second) + ")").c_str());
            }

            Assert::IsTrue(resultPath == expectedPath);
        }

        TEST_METHOD(TestNextStep)
        {
            Maze maze(10, 10);
            std::pair<int, int> current = { 5, 5 };
            std::pair<int, int> next = maze.nextStep(current);
            Assert::IsTrue(maze.isValidPosition(next));
        }

        TEST_METHOD(TestGenerateMaze)
        {
            Maze maze(10, 10);
            maze.generateMaze(10, 10);
            Assert::IsTrue(maze.inMaze.size() == 100);
        }
    };
}
