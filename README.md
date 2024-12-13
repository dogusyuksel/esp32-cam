# sat-cam
Common Library for satellite cameras for earth observation mission


bool init_session() {
    // a tag and and some hint must be given to calculate should-be-allocated-memory
    // this is dragonfly style
    // after open session, there is activate session command for simra to do that
    // flight direction
}


bool open_session() {
    // add a packet
}


bool close_session() {
    // add a packet
}

bool get_session_id() {
    // a command to read the session id and allocated memory for the session
}

bool get_sensor_parameters() {
    // after set, get it to check
}

bool set_sensor_parameters() {
    // what are these, these are generally sensor related just before SENSOR_ON command
    // pga gain, adc gain, offsett
}

bool sensor_on() {

}

bool sensor_off() {

}

bool get_capturing_parameters() {
    // after set, get it to check
}

bool set_capturing_parameters() {
    // integration time
    // mode (line or frame)
    // number of capture
}

bool start_capture() {
    // imager and sensor config, capturing config (3 packets) could be generated directly
}

bool get_version() {
    //get the version number
}

bool read_status() {
    // should give hint about the state (like capturing done)
}

bool imager_memory_structure() {
    //should return data about saved sessions inside the imager somehow
}

bool delete_session(session id) {
    // add packet
}


enable_pps
    // can get RISING or FALLING EDGE (or both)
    // add packet on each pss trigger

inject_custom_ancillary
    // inject packet when called


get-session-info(session id)
    // check totalm memery and prepared for dma

readout (session_id)


readout-partially(band_filter, or line number filter)






https://www.doxygen.nl/manual/install.html



https://www.doxygen.nl/download.html