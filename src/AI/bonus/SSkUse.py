import joblib
import sys
import argparse
import timeit
import pandas as pd

predictions = []


class Argparse(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write("error: %s\n" % message)
        self.print_help()
        sys.exit(84)


def makePredictions():
    clf.predict(XTestData)


if __name__ == "__main__":
    argParser = Argparse(description="Use CSV file for Zappy IA to test tree")

    argParser.add_argument("-f", "--file", help="CSV file to use", required=True)
    argParser.add_argument("-t", "--tree", help="Tree to use (.joblib)", required=True)
    argParser.add_argument(
        "-b", "--benchmark", action="store_true", help="Run benchmark", required=False
    )

    try:
        clf = joblib.load(argParser.parse_args().tree)
    except FileNotFoundError:
        print("Error: Tree file not found")
        sys.exit(84)

    try:
        testData = pd.read_csv(argParser.parse_args().file)
    except FileNotFoundError:
        print("Error: CSV file not found")
        sys.exit(84)

    XTestData = testData.drop(columns=["response"])

    if argParser.parse_args().benchmark:
        prediction_time = timeit.timeit(makePredictions, number=100)
        num_rows = XTestData.shape[0]
        print(
            f"Time taken to make predictions: {prediction_time:.6f} seconds for {num_rows} rows"
        )
        avg_prediction_time_per_row = prediction_time / num_rows
        print(
            f"Average time taken to make predictions: {avg_prediction_time_per_row:.6f} seconds per row"
        )

    else:
        predictions = clf.predict(XTestData)
        for prediction in predictions:
            print(prediction)
