module Standard.String;

header function concatenate (stringA: String, stringB: String): String;

header function getIndex (string: String, index: Integer): String;
header function setIndex (string: String, index: Integer, character: String);

header function getIndexByte (string: String, index: Integer): Integer;
header function setIndexByte (string: String, index: Integer, value: Integer);

header function getLength (string: String): Integer;
