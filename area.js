const mongoose = require('mongoose');

const areaSchema = new mongoose.Schema({
  area: String,
  montion_detected: Boolean,
  timestamp: timestamp,
});

module.exports = mongoose.model('Area', areaSchema);
