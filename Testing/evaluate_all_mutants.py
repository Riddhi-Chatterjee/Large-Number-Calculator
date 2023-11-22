import evaluate_mutant as em
from revert_to_original_code import revert
import pandas as pd
from tqdm import tqdm

filestring = ""
with open("mutations.txt", "r") as m:
    for line in m:
        filestring += line
        
mutations  = [x.split("\n") for x in filestring.split("\n\n")[:-1]]

tests_dict = {}
with open("test_cases.txt", "r") as t:    
    for line in t:
        if line.split(" : ")[0] not in tests_dict.keys():
            tests_dict[line.split(" : ")[0]] = [line.split("\n")[0]]
        else:
            tests_dict[line.split(" : ")[0]].append(line.split("\n")[0])

orig_prog_test_data = em.test_original_program(tests_dict)

df = pd.DataFrame([])

for mutation in tqdm(mutations, desc = "Progress"):
    em.create_mutant(mutation)

    mutant_test_data = em.test_mutant(mutation, tests_dict, orig_prog_test_data)
    
    revert()

    #Creating the auto_run_report's dataframe:
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

df.to_csv("auto_run_report.csv", index=False) 
