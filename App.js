import React, { useState } from "react";
import { View, Text, TouchableOpacity, StyleSheet } from "react-native";

export default function App() {
  const [isLedOn, setLedState] = useState(false);

  const toggleLed = async () => {
    try {
      const response = await fetch("http://192.168.1.55/onoff", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ isLedOn: !isLedOn }),
      });
      if (response.ok) {
        setLedState(!isLedOn);
      }
    } catch (error) {
      console.error("Error toggling LED:", error);
    }
  };

  return (
    <View style={{ flex: 1, justifyContent: "center", alignItems: "center" }}>
      <Text>NodeMCU LED Control</Text>
      <TouchableOpacity onPress={toggleLed} style={[styles.btn , {backgroundColor: isLedOn ? "red" : "green"}]}>
        <Text>{isLedOn ? "Turn Off LED" : "Turn On LED"}</Text>
      </TouchableOpacity>
    </View>
  );
}

const styles = StyleSheet.create({
  btn: {
    marginVertical:20,
    padding:24,
    borderRadius:4,
    elevation:4
  }
})
