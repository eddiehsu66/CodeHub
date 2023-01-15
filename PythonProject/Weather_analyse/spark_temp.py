from pyspark.sql import SparkSession

if __name__ == '__main__':
    spark = SparkSession.builder.master("local").appName("demo").getOrCreate()
    dataFrame = spark.read.option("header", True).option("delimiter", "\t").csv("/data/*")
    dataFrame.createTempView("data")
    dataFrame.show()
    spark.stop()