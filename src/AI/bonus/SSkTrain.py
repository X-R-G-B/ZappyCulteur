import pydotplus
import joblib
import sys
import argparse
import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.tree import export_graphviz
from IPython.display import Image


class Argparse(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write("error: %s\n" % message)
        self.print_help()
        sys.exit(84)


if __name__ == "__main__":
    argParser = Argparse(description="Train Zappy IA")

    argParser.add_argument("-f", "--file", help="CSV file to train", required=True)

    args = argParser.parse_args()
    fileName = args.file

    try:
        df = pd.read_csv(fileName)
    except:
        print("Error: file not found")
        sys.exit(84)

    X = df.drop(columns=["response"], axis=1)
    y = df["response"]

    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    clf = DecisionTreeClassifier(min_samples_leaf=5, max_depth=5, min_samples_split=10)

    clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)

    accuracy = accuracy_score(y_test, y_pred)
    print("Accuracy: " + str(accuracy))

    joblib.dump(clf, fileName.split(".")[0] + ".joblib")

    dot_data = export_graphviz(
        clf, out_file=None, feature_names=X.columns, class_names=y.unique()
    )
    graph = pydotplus.graph_from_dot_data(dot_data)
    Image(graph.create_png())
    graph.write_png(fileName.split(".")[0] + ".png")
