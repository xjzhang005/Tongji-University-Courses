`timescale 1ns / 1ps

module testbench;

    // Inputs
    reg clk;
    reg rst_n;
    reg key;

    // Outputs
    wire [6:0] led;
    wire [7:0] an;
    wire light;

    // Instantiate the Unit Under Test (UUT)
    keying uut (
        .clk(clk),
        .rst_n(rst_n),
        .key(key),
        .led(led),
        .an(an),
        .light(light)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk;  // 100MHz clock (10ns period)
    end

    // Stimulus
    initial begin
        // Initialize inputs
        rst_n = 0;
        key = 0;
        
        // Apply reset
        #10 rst_n = 1;  // Release reset after 10ns
        
        // Test key press
        #100 key = 1;    // Press key after 100ns
        #1000 key = 0;   // Release key after 1000ns (simulate key press duration)

        // Test another key press
        #2000 key = 1;   // Press key again after 2000ns
        #500 key = 0;    // Release key after 500ns (simulate short key press)

        // Test long key press
        #1000 key = 1;   // Press key after 1000ns
        #2000 key = 0;   // Release key after 2000ns

        // End simulation after a few more cycles
        #5000 $finish;
    end

    // Monitor the outputs
    initial begin
        $monitor("At time %t, key = %b, led = %b, an = %b, light = %b", $time, key, led, an, light);
    end

endmodule
