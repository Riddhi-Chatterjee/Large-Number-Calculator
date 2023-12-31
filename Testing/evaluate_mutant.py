import subprocess
import os
from os.path import exists
import pandas as pd

def test_original_program(tests_dict):
    executable_created = {}
    results = {}
    for key in tests_dict.keys():
        results[key] = []
        
        if key.split("_")[0] == "adder":
            #Create the executable file corresponding to the key:
            if(key.split("_")[0]+"_tester" not in executable_created.keys()):
                cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp"]
                subprocess.check_output(cmd1, text=True)
                executable_created[key.split("_")[0]+"_tester"] = True
            
            for test in tests_dict[key]:
                try:
                    cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                    test_result = subprocess.check_output(cmd2, text=True)
                    results[key].append(test_result)
                except subprocess.CalledProcessError as e:
                    # Handle any errors that occurred during the command execution
                    print("Subprocess command execution error:", e)
                    results[key].append("FAILURE_"+str(e))
                
                
        elif key.split("_")[0] == "approximator":
            #Create the executable file corresponding to the key:
            if(key.split("_")[0]+"_tester" not in executable_created.keys()):
                cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp"]
                subprocess.check_output(cmd1, text=True)
                executable_created[key.split("_")[0]+"_tester"] = True
            
            for test in tests_dict[key]:
                try:
                    cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                    test_result = subprocess.check_output(cmd2, text=True)
                    results[key].append(test_result)
                except subprocess.CalledProcessError as e:
                    # Handle any errors that occurred during the command execution
                    print("Subprocess command execution error:", e)
                    results[key].append("FAILURE_"+str(e))
                
                
        elif key.split("_")[0] == "baseConverter":
            #Create the executable file corresponding to the key:
            if(key.split("_")[0]+"_tester" not in executable_created.keys()):
                cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../adder.cpp", "../divider.cpp", "../approximator.cpp"]
                subprocess.check_output(cmd1, text=True)
                executable_created[key.split("_")[0]+"_tester"] = True
            
            for test in tests_dict[key]:
                try:
                    cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                    test_result = subprocess.check_output(cmd2, text=True)
                    results[key].append(test_result)
                except subprocess.CalledProcessError as e:
                    # Handle any errors that occurred during the command execution
                    print("Subprocess command execution error:", e)
                    results[key].append("FAILURE_"+str(e))
                
                
        elif key.split("_")[0] == "divider":
            #Create the executable file corresponding to the key:
            if(key.split("_")[0]+"_tester" not in executable_created.keys()):
                cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp"]
                subprocess.check_output(cmd1, text=True)
                executable_created[key.split("_")[0]+"_tester"] = True
            
            for test in tests_dict[key]:
                try:
                    cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                    test_result = subprocess.check_output(cmd2, text=True)
                    results[key].append(test_result)
                except subprocess.CalledProcessError as e:
                    # Handle any errors that occurred during the command execution
                    print("Subprocess command execution error:", e)
                    results[key].append("FAILURE_"+str(e))
                
                
        elif key.split("_")[0] == "multiplier":
            #Create the executable file corresponding to the key:
            if(key.split("_")[0]+"_tester" not in executable_created.keys()):
                cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp", "../adder.cpp", "../subtractor.cpp"]
                subprocess.check_output(cmd1, text=True)
                executable_created[key.split("_")[0]+"_tester"] = True
            
            for test in tests_dict[key]:
                try:
                    cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                    test_result = subprocess.check_output(cmd2, text=True)
                    results[key].append(test_result)
                except subprocess.CalledProcessError as e:
                    # Handle any errors that occurred during the command execution
                    print("Subprocess command execution error:", e)
                    results[key].append("FAILURE_"+str(e))
                
                
        elif key.split("_")[0] == "squareRoot":
            #Create the executable file corresponding to the key:
            if(key.split("_")[0]+"_tester" not in executable_created.keys()):
                cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp", "../baseConverter.cpp", "../multiplier.cpp", "../divider.cpp", "../adder.cpp", "../subtractor.cpp"]
                subprocess.check_output(cmd1, text=True)
                executable_created[key.split("_")[0]+"_tester"] = True
            
            for test in tests_dict[key]:
                try:
                    cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                    test_result = subprocess.check_output(cmd2, text=True)
                    results[key].append(test_result)
                except subprocess.CalledProcessError as e:
                    # Handle any errors that occurred during the command execution
                    print("Subprocess command execution error:", e)
                    results[key].append("FAILURE_"+str(e))
                
                
        elif key.split("_")[0] == "subtractor":
            #Create the executable file corresponding to the key:
            if(key.split("_")[0]+"_tester" not in executable_created.keys()):
                cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp"]
                subprocess.check_output(cmd1, text=True)
                executable_created[key.split("_")[0]+"_tester"] = True
            
            for test in tests_dict[key]:
                try:
                    cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                    test_result = subprocess.check_output(cmd2, text=True)
                    results[key].append(test_result)
                except subprocess.CalledProcessError as e:
                    # Handle any errors that occurred during the command execution
                    print("Subprocess command execution error:", e)
                    results[key].append("FAILURE_"+str(e))
                
        
        elif key == "Main_calculator":
            #Create the executable file corresponding to the key:
            if(key.split("_")[0]+"_tester" not in executable_created.keys()):
                cmd1 = ["g++", "-o", key.split("_")[0]+"_test", "../"+key.split("_")[0]+".cpp", "../adder.cpp", "../approximator.cpp", "../baseConverter.cpp", "../divider.cpp", "../multiplier.cpp", "../squareRoot.cpp", "../subtractor.cpp"]
                subprocess.check_output(cmd1, text=True)
                executable_created[key.split("_")[0]+"_tester"] = True
            
            for test in tests_dict[key]:
                try:
                
                    #Get the stdin values:
                    input_values = " ".join(test.split(" : ")[2:-1])
                    
                    #Get the expected output:
                    expected_output = test.split(" : ")[-1]
                    
                    # Run the C++ program using subprocess
                    process = subprocess.Popen("./"+key.split("_")[0]+"_test", stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
                    
                    # Provide input to the C++ program
                    process.stdin.write(input_values)
                    process.stdin.flush()

                    # Wait for the C++ program to finish and get the output
                    output, error = process.communicate() #error is None if there is no error
                    
                    # Close the input stream
                    process.stdin.close()
                    
                    # Check whether the test case passed or not
                    test_result = ""
                    if expected_output not in str(output):
                        test_result = "FAILURE_"+str(output)+str(error)
                    else:
                        if error == "":
                            if "ERROR: " in expected_output:
                                output = str(output)
                                truncated_output = output.split("ERROR: ")[1].split("\n\n")[0]
                                expected_output = expected_output.split("ERROR: ")[1]
                                
                                if truncated_output == expected_output:
                                    test_result = "SUCCESS_"+output
                                else:
                                    test_result = "FAILURE_"+output
                            else:
                                computation = expected_output.split(" = ")[0]
                                computation = computation + " = "
                                output = str(output)
                                truncated_output = output.split(computation)[1].split("\n\n")[0]
                                truncated_output = computation + truncated_output
                                
                                if truncated_output == expected_output:
                                    test_result = "SUCCESS_"+output
                                else:
                                    test_result = "FAILURE_"+output
                        else:
                            test_result = "FAILURE_"+str(output)+str(error)
                    
                    results[key].append(test_result)
                
                except subprocess.CalledProcessError as e:
                    # Handle any errors that occurred during the command execution
                    print("Subprocess command execution error:", e)
                    results[key].append("FAILURE_"+str(e))
                
                
        
        elif key == "":
            pass
        #... add support for different keys
    
    for key in executable_created.keys():
        os.remove(key[:-2]) #Removing the executable files
    
    return results
            

def test_mutant(mutation, tests_dict, orig_prog_test_data):
    results = {}
    key = mutation[0].split(" : ")[0]
    executable = ""
    orig_prog_results = orig_prog_test_data[key]
    
    mutation_descriptor = ""
    for i, ele in enumerate(mutation):
        if i == 0:
            mutation_descriptor += ele
        else:
            mutation_descriptor += ("\n" + ele)
        
    results["Mutant"] = mutation_descriptor
    results["Differentiating_test_case"] = "NA"
    results["Test_result_of_original_program"] = "NA"
    results["Test_result_of_mutant"] = "NA"
    results["Test_output_of_original_program"] = "NA"
    results["Test_output_of_mutant"] = "NA"
    results["Mutant_status"] = "Not killed"
    
    if key.split("_")[0] == "adder":
        #Create the executable file corresponding to the key:
        cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp"]
        subprocess.check_output(cmd1, text=True)
        executable = key.split("_")[0]+"_test"
        
        for i, test in enumerate(tests_dict[key]):
            try:
                cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                test_result = subprocess.check_output(cmd2, text=True)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
            except subprocess.CalledProcessError as e:
                # Handle any errors that occurred during the command execution
                print("Subprocess command execution error:", e)
                test_result = "FAILURE_"+str(e)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
    
    elif key.split("_")[0] == "approximator":
        #Create the executable file corresponding to the key:
        cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp"]
        subprocess.check_output(cmd1, text=True)
        executable = key.split("_")[0]+"_test"
        
        for i, test in enumerate(tests_dict[key]):
            try:
                cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                test_result = subprocess.check_output(cmd2, text=True)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
            except subprocess.CalledProcessError as e:
                # Handle any errors that occurred during the command execution
                print("Subprocess command execution error:", e)
                test_result = "FAILURE_"+str(e)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
            
    elif key.split("_")[0] == "baseConverter":
        #Create the executable file corresponding to the key:
        cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../adder.cpp", "../divider.cpp", "../approximator.cpp"]
        subprocess.check_output(cmd1, text=True)
        executable = key.split("_")[0]+"_test"
        
        for i, test in enumerate(tests_dict[key]):
            try:
                cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                test_result = subprocess.check_output(cmd2, text=True)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break   
            except subprocess.CalledProcessError as e:
                # Handle any errors that occurred during the command execution
                print("Subprocess command execution error:", e)
                test_result = "FAILURE_"+str(e)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed" 
                    break  
    
    elif key.split("_")[0] == "divider":
        #Create the executable file corresponding to the key:
        cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp"]
        subprocess.check_output(cmd1, text=True)
        executable = key.split("_")[0]+"_test"
        
        for i, test in enumerate(tests_dict[key]):
            try:
                cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                test_result = subprocess.check_output(cmd2, text=True)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
            except subprocess.CalledProcessError as e:
                # Handle any errors that occurred during the command execution
                print("Subprocess command execution error:", e)
                test_result = "FAILURE_"+str(e)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
            
    elif key.split("_")[0] == "multiplier":
        #Create the executable file corresponding to the key:
        cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp", "../adder.cpp", "../subtractor.cpp"]
        subprocess.check_output(cmd1, text=True)
        executable = key.split("_")[0]+"_test"
        
        for i, test in enumerate(tests_dict[key]):
            try:
                cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                test_result = subprocess.check_output(cmd2, text=True)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
            except subprocess.CalledProcessError as e:
                # Handle any errors that occurred during the command execution
                print("Subprocess command execution error:", e)
                test_result = "FAILURE_"+str(e)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
    
    elif key.split("_")[0] == "squareRoot":
        #Create the executable file corresponding to the key:
        cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp", "../baseConverter.cpp", "../multiplier.cpp", "../divider.cpp", "../adder.cpp", "../subtractor.cpp"]
        subprocess.check_output(cmd1, text=True)
        executable = key.split("_")[0]+"_test"
        
        for i, test in enumerate(tests_dict[key]):
            try:
                cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                test_result = subprocess.check_output(cmd2, text=True)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
            except subprocess.CalledProcessError as e:
                # Handle any errors that occurred during the command execution
                print("Subprocess command execution error:", e)
                test_result = "FAILURE_"+str(e)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
    
    elif key.split("_")[0] == "subtractor":
        #Create the executable file corresponding to the key:
        cmd1 = ["g++", "-o", key.split("_")[0]+"_test", key.split("_")[0]+"_tester.cpp", "../"+key.split("_")[0]+".cpp", "../approximator.cpp"]
        subprocess.check_output(cmd1, text=True)
        executable = key.split("_")[0]+"_test"
        
        for i, test in enumerate(tests_dict[key]):
            try:
                cmd2 = ["./"+key.split("_")[0]+"_test", '_'.join(key.split("_")[1:])] + test.split(" : ")[2:]
                test_result = subprocess.check_output(cmd2, text=True)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
            except subprocess.CalledProcessError as e:
                # Handle any errors that occurred during the command execution
                print("Subprocess command execution error:", e)
                test_result = "FAILURE_"+str(e)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
    
    elif key == "Main_calculator":
        #Create the executable file corresponding to the key:
        cmd1 = ["g++", "-o", key.split("_")[0]+"_test", "../"+key.split("_")[0]+".cpp", "../adder.cpp", "../approximator.cpp", "../baseConverter.cpp", "../divider.cpp", "../multiplier.cpp", "../squareRoot.cpp", "../subtractor.cpp"]
        subprocess.check_output(cmd1, text=True)
        executable = key.split("_")[0]+"_test"
        
        for i, test in enumerate(tests_dict[key]):
            try:
            
                #Get the stdin values:
                input_values = " ".join(test.split(" : ")[2:-1])
                
                #Get the expected output:
                expected_output = test.split(" : ")[-1]
                
                # Run the C++ program using subprocess
                process = subprocess.Popen("./"+key.split("_")[0]+"_test", stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
                
                # Provide input to the C++ program
                process.stdin.write(input_values)
                process.stdin.flush()

                # Wait for the C++ program to finish and get the output
                output, error = process.communicate() #error is None if there is no error
                
                # Close the input stream
                process.stdin.close()
                
                # Check whether the test case passed or not
                test_result = ""
                if expected_output not in str(output):
                    test_result = "FAILURE_"+str(output)+str(error)
                else:
                    if error == "":
                        if "ERROR: " in expected_output:
                            output = str(output)
                            truncated_output = output.split("ERROR: ")[1].split("\n\n")[0]
                            expected_output = expected_output.split("ERROR: ")[1]
                            
                            if truncated_output == expected_output:
                                test_result = "SUCCESS_"+output
                            else:
                                test_result = "FAILURE_"+output
                        else:
                            computation = expected_output.split(" = ")[0]
                            computation = computation + " = "
                            output = str(output)
                            truncated_output = output.split(computation)[1].split("\n\n")[0]
                            truncated_output = computation + truncated_output
                            
                            if truncated_output == expected_output:
                                test_result = "SUCCESS_"+output
                            else:
                                test_result = "FAILURE_"+output
                    else:
                        test_result = "FAILURE_"+str(output)+str(error)
                
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
            
            except subprocess.CalledProcessError as e:
                # Handle any errors that occurred during the command execution
                print("Subprocess command execution error:", e)
                test_result = "FAILURE_"+str(e)
                if test_result != orig_prog_results[i]: #Mutant killed by this test case
                    results["Differentiating_test_case"] = test
                    results["Test_result_of_original_program"] = orig_prog_results[i].split("_")[0]
                    results["Test_result_of_mutant"] = test_result.split("_")[0]
                    results["Test_output_of_original_program"] = '_'.join(orig_prog_results[i].split("_")[1:])
                    results["Test_output_of_mutant"] = '_'.join(test_result.split("_")[1:])
                    results["Mutant_status"] = "Killed"
                    break
                
    elif key == "":
        pass
    #... add support for different keys
    os.remove(executable)
    
    return results

def create_manual_run_report(mutant_test_data):
    df = pd.DataFrame([])
    if(exists("manual_run_report.csv")):
        df = pd.read_csv("manual_run_report.csv")
        
    #Removing the last row of df...
    df.drop(df.tail(1).index,inplace=True)
    
    new_row = pd.DataFrame([mutant_test_data])
    df = pd.concat([df, new_row], ignore_index=True)
    
    #Calculating kill_num and kill_frac..
    kill_num = df['Mutant_status'].value_counts().get('Killed', 0)
    kill_frac = kill_num/df.shape[0]
    
    last_row = {}
    last_row["Mutant"] = ""
    last_row["Differentiating_test_case"] = ""
    last_row["Test_result_of_original_program"] = ""
    last_row["Test_result_of_mutant"] = ""
    last_row["Test_output_of_original_program"] = ""
    last_row["Test_output_of_mutant"] = ""
    last_row["Mutant_status"] = "Mutants killed = "+str(kill_num)+"/"+str(df.shape[0])+" = "+str(round(kill_frac*100, 2))+"%"
    
    last_row = pd.DataFrame([last_row])
    df = pd.concat([df, last_row], ignore_index=True)
    
    df.to_csv("manual_run_report.csv", index=False) 

def create_mutant(mutation):
    
    for change in mutation:
        
        attributes = change.split(" : ")
        title = attributes[0]
        function_name = title.split("_")[1]
        opt_code = attributes[1]
        filename = attributes[2]
        start_line_no = int(attributes[3]) - 1
        start_column_no = int(attributes[4]) - 1
        end_line_no = int(attributes[5]) - 1
        end_column_no = int(attributes[6]) - 1 - 1
        replacement_lines = attributes[7:]
        
        filestring = ""
        sum_s = 0
        sum_e = 0
        with open("../"+filename, "r") as f:
            for i, line in enumerate(f):
                if(i < start_line_no):
                    sum_s += len(line)
                if(i < end_line_no):
                    sum_e += len(line)
                filestring += line
                
        with open("../original_"+filename, "w") as bkp_f:
            bkp_f.write(filestring)
        
        start_index = sum_s + start_column_no
        end_index = sum_e + end_column_no
        
        first_half = filestring[:start_index]
        second_half = filestring[end_index+1:]
        
        for i, line in enumerate(replacement_lines):
            if(i != 0):
                first_half += ("\n" + line)
            else:
                first_half += line
        
        filestring = first_half + second_half
        
        with open("../"+filename, "w") as f:
            f.write(filestring)
            
        


if __name__ == "__main__":
    mut_num = int(input("Enter the line number of the mutation from mutations.txt: "))
    mutation = [] #Represents some change made in the original program

    with open("mutations.txt", "r") as m:
        line_no = 1
        flag = False
        for line in m:
            if line_no == mut_num:
                flag = True
            if flag and line == "\n":
                break
            if flag:
                mutation.append(line.split("\n")[0])
            line_no += 1

    tests = []
    with open("test_cases.txt", "r") as t:    
        for line in t:
            if mutation[0].split(" : ")[0] == line.split(" : ")[0]:
                tests.append(line.split("\n")[0])
        
    tests_dict = {}
    tests_dict[mutation[0].split(" : ")[0]] = tests

    orig_prog_test_data = test_original_program(tests_dict)

    create_mutant(mutation)

    mutant_test_data = test_mutant(mutation, tests_dict, orig_prog_test_data)

    create_manual_run_report(mutant_test_data)
