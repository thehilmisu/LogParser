#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define             PARSE_STATE             0
#define             SEARCH_STATE            1
#define             FILE_NOT_READ           2
#define             IDLE_STATE              3
#define             EXTRACT_TEST_CYCLES     4
#define             INITIALIZE_CYCLES       5
#define             OPEN_FILE               6
#define             SEARCH_STATE_WAIT       7

#define             SEARCH_TYPE_NORMAL      0
#define             SEARCH_TYPE_REGEX       1
#define             SEARCH_TYPE_REGEXM      2

#define             TEST_CYCLE_END          "#############################"

#define             WIFI_START_WORKER       "Wifi: startWorker"
#define             FAIL_NOT_STARTED        "fail: info: not started"
#define             RESULT_WIFI_FAIL        "result testcase: #Wifi: FAIL"
#define             RESULT_DAB_FAIL         "result testcase: #Check_DAB: FAIL"
#define             TUNER_WRITE_FAIL        "fail: error:write_failed;"
#define             TUNER_WORKER_STATUS     "TunerworkerNGNXP:status"

#define             ROW                     "\\b92054\\b"
#define             NAR                     "\\b91954\\b"
#define             CHN                     "\\b92154\\b"



#endif // DEFINITIONS_H
